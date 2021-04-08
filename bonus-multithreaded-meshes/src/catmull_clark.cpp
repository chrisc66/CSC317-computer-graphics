#include "catmull_clark.h"
#include "vertex_triangle_adjacency.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>

#include <thread>
#include <mutex>

std::mutex SV_mutex;
std::mutex FC_mutex;
std::mutex FE_mutex;


// Get the center point of four given points
Eigen::Vector3d inline get_center(Eigen::Vector3d p1, Eigen::Vector3d p2, Eigen::Vector3d p3, Eigen::Vector3d p4) {
	Eigen::Vector3d center;
	for (int i = 0; i < 3; ++i) {
		center(i) = (p1(i) + p2(i) + p3(i) + p4(i)) / 4;
	}
	return center;
}



// Step One
void step_one_thread_start (
  const int i,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & SV, 
  Eigen::MatrixXi & FC)
{
	Eigen::Vector3d p1, p2, p3, p4;
	for (int j = 0; j < 3; ++j) {
		p1(j) = SV(F(i, 0), j);
		p2(j) = SV(F(i, 1), j);
		p3(j) = SV(F(i, 2), j);
		p4(j) = SV(F(i, 3), j);
	}
	Eigen::Vector3d center_point = get_center(p1,p2,p3,p4);

	SV_mutex.lock();
	int sv_rows = SV.rows();
	FC_mutex.lock();
	FC(i,0) = sv_rows;
	FC_mutex.unlock();
	SV.conservativeResize(sv_rows + 1, 3);
	for (int j = 0; j < 3; ++j){
		SV(sv_rows, j) = center_point(j);
	}
	SV_mutex.unlock();
}



// Step Two and Three
void step_two_three_thread_start (
  const int i,
  const int j,
  const Eigen::MatrixXi & F,
  const std::vector< std::vector<int> > & VF,
  const Eigen::MatrixXi & FC,
  Eigen::MatrixXd & SV, 
  Eigen::MatrixXi & FE)
{
	
	
	// find adjacent faces vectors
	std::vector<int> Fj1 = VF[F(i, j)];
	std::vector<int> Fj2 = VF[F(i, (j+1)%4)];

	// find neighbouring face
	int neighbour_face_idx = 0;
	for (int k = 0; k < Fj1.size(); ++k) {
		for (int l = 0; l < Fj2.size(); ++l) {
			if (Fj1[k] == Fj2[l] && Fj1[k] != i) {
				// found, break out of the for loop
				neighbour_face_idx = Fj1[k];
				k = Fj1.size();
				l = Fj2.size();
				break;
			}
		}
	}

	// find edges centers
	int edge_idx = -1;
	bool found_edge = false;
	FE_mutex.lock();
	for (int k = 0; k < 4; ++k) {
		if (FE(neighbour_face_idx, k) == 0)
			continue;
		if (F(neighbour_face_idx, k) == F(i, j) || F(neighbour_face_idx, k) == F(i, (j+1)%4)) {
			edge_idx = k;
			if (F(neighbour_face_idx, k+1) == F(i, j) || F(neighbour_face_idx, k+1) == F(i, (j+1)%4)) 
				FE(i, j) = FE(neighbour_face_idx, edge_idx);
			else 
				FE(i, j) = FE(neighbour_face_idx, 3);
			found_edge = true;
			break;
		}
	}

	if (found_edge){
		FE_mutex.unlock();
		return;
	}

	Eigen::Vector3d p1, p2, p3, p4;
	for (int k = 0; k < 3; ++k) {
		p1(k) = SV(F(i, j), k);
		p2(k) = SV(F(i, (1 + j) % 4), k);
		p3(k) = SV(FC(i, 0), k);
		p4(k) = SV(FC(neighbour_face_idx, 0), k);
	}
	Eigen::Vector3d center_point = get_center(p1, p2, p3, p4);

	SV_mutex.lock();
	int sv_rows = SV.rows();
	FE(i, j) = sv_rows;
	FE_mutex.unlock();
	SV.conservativeResize(sv_rows + 1, 3);
	for (int k = 0; k < 3; ++k){
		SV(sv_rows, k) = center_point(k);
	}
	SV_mutex.unlock();
}



// Step Four
void step_four_thread_start (
  const int i,
  const Eigen::MatrixXi & F,
  const std::vector< std::vector<int> > & VF,
  const Eigen::MatrixXi & FC,
  const Eigen::MatrixXi & FE,
  Eigen::MatrixXd & SV)
{
	Eigen::Vector3d cur_vertex = Eigen::Vector3d::Zero();
	Eigen::Vector3d next_vertex = Eigen::Vector3d::Zero();
	for (int j = 0; j < VF[i].size(); ++j) {
		int nf = VF[i][j];
		for (int k = 0; k < 3; ++k){
			cur_vertex(k) += SV(FC(nf, 0), k);
		}

		for (int k = 0; k < F.cols(); ++k) {
			if (F(nf, k) != i) {
				continue;
			}
			for (int l = 0; l < 3; ++l){
				next_vertex(l) += SV(FE(nf, k), l) + SV(FE(nf, (k + 3) % 4), l);
			}
			break;
		}
	}

	cur_vertex = cur_vertex / VF[i].size();
	next_vertex = next_vertex / (2*VF[i].size());
	SV_mutex.lock();
	for (int k = 0; k < 3; ++k){
		SV(i, k) = (cur_vertex(k) + 2 * next_vertex(k) + (VF[i].size() - 3) * SV(i, k)) / VF[i].size();
	}
	SV_mutex.unlock();
}



void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
    ////////////////////////////////////////////////////////////////////////////
  	// Replace with your code here:

  	// Base case: do nothing if num_iters = 0
  	if (num_iters == 0){
    	return;
  	}

	// General case: compute catmull clark
	SV = V;
	SF.resize(F.rows() * 4, 4);

	// Face Center matrix
	Eigen::MatrixXi FC = Eigen::MatrixXi::Zero(F.rows(),1);

	// Vertex Face adjacency matrix
	std::vector< std::vector<int> > VF;
	vertex_triangle_adjacency(F, V.rows(), VF);

	// Step 1: Get center point of each face
	std::vector<std::thread> step_one_threads;
	for (int i = 0; i < F.rows(); ++i) {
		step_one_threads.push_back(std::thread(step_one_thread_start, i, F, std::ref(SV), std::ref(FC)));
	}
	for (std::thread & t : step_one_threads){
		if (t.joinable())
			t.join();
	}
	
	// Step 2 & 3
	// Get center point of each edge
	// Add edges between face center and edge center points
	std::vector<std::thread> step_two_three_threads;
	Eigen::MatrixXi FE = Eigen::MatrixXi::Zero(F.rows(),4);
	for (int i = 0; i < F.rows(); ++i) {
		for (int j = 0; j < 4; ++j) {
			step_two_three_threads.push_back(std::thread(step_two_three_thread_start, i, j, F, VF, FC, std::ref(SV), std::ref(FE)));
		}
	}
	for (std::thread & t : step_two_three_threads){
		if (t.joinable())
			t.join();
	}

	// Step 4: move origin vertex
	std::vector<std::thread> step_four_threads;
	for (int i = 0; i < V.rows(); ++i) {
		step_four_threads.push_back(std::thread(step_four_thread_start, i, F, VF, FC, FE, std::ref(SV)));
	}
	for (std::thread & t : step_four_threads){
		if (t.joinable())
			t.join();
	}
	
	// Step 5: Connect points and create new meshes
	// no need to multi-thread in this step
	for (int i = 0; i < F.rows(); ++i) {
		for (int k = 0; k < 4; ++k) {
			SF(4*i+k, 0) = FE(i, (k+3)%4);
			SF(4*i+k, 1) =  F(i, k);
			SF(4*i+k, 2) = FE(i, k);
			SF(4*i+k, 3) = FC(i, 0);
		}
	} 

	// Recursive call: with SV and SF values
	Eigen::MatrixXd old_V = SV;
	Eigen::MatrixXi old_F = SF;
	catmull_clark(old_V, old_F, num_iters-1, SV, SF);

	////////////////////////////////////////////////////////////////////////////

	return;
}

