/*
 * file: KDTree.hpp
 * author: J. Frederico Carvalho
 *
 * This is an adaptation of the KD-tree implementation in rosetta code
 * https://rosettacode.org/wiki/K-d_tree
 *
 * It is a reimplementation of the C code using C++.  It also includes a few
 * more queries than the original, namely finding all points at a distance
 * smaller than some given distance to a point.
 *
 */

#include <algorithm>
#include <cmath>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <vector>

#include "core/KDTree.hpp"

KDNode::KDNode() = default;

//KDNode::KDNode(const halftoneparticle::Particle &p, const size_t &idx_, const KDNodePtr &left_,
//               const KDNodePtr &right_) {
//    particle_ = p;
//    x = point_t ({particle_.position().x,particle_.position().y});
//    index = idx_;
//    left = left_;
//    right = right_;
//}

KDNode::KDNode(halftoneparticle::Particle &p, const KDNodePtr &left_,
               const KDNodePtr &right_) {
    particle_ = p;
    x = point_t({particle_.position().x, particle_.position().y});
    index = particle_.age();
    left = left_;
    right = right_;
}

KDNode::~KDNode() = default;

//double KDNode::coord(const size_t &idx) { return x.at(idx); }
//halftoneparticle::Particle KDNode::GetParticle() { return particle_; }
KDNode::operator bool() { return (!x.empty()); }
//KDNode::operator point_t() { return x; }
//KDNode::operator size_t() { return index; }
//KDNode::operator pointIndex() { return pointIndex(x, index); }

KDNodePtr NewKDNodePtr() {
    KDNodePtr mynode = std::make_shared<KDNode>();
    return mynode;
}

inline double dist2(const glm::vec2 &a, const glm::vec2 &b) {
    //double distc = 0;
    //    for (size_t i = 0; i < a.size(); i++) {
    //        double di = a.at(i) - b.at(i);
    //        distc += di * di;
    //    }
    return glm::distance(a, b);
    //return distc;
}

inline double dist2(const KDNodePtr &a, const KDNodePtr &b) {
    return dist2(a->particle_.position(), b->particle_.position());
}

//inline double dist(const point_t &a, const point_t &b) {
//    return std::sqrt(dist2(a, b));
//}
//
//inline double dist(const KDNodePtr &a, const KDNodePtr &b) {
//    return std::sqrt(dist2(a, b));
//}

comparer::comparer(size_t idx_) : idx{idx_} {};

inline bool comparer::compare_idx(const pointIndex &a,//
                                  const pointIndex &b //
) {
    return (a.first.at(idx) < b.first.at(idx));//
}

inline void sort_on_idx(const pointIndexArr::iterator &begin,//
                        const pointIndexArr::iterator &end,  //
                        size_t idx) {
    comparer comp(idx);
    comp.idx = idx;

    using std::placeholders::_1;
    using std::placeholders::_2;

    std::nth_element(begin, begin + std::distance(begin, end) / 2,
                     end, std::bind(&comparer::compare_idx, comp, _1, _2));
}

using pointVec = std::vector<point_t>;

KDNodePtr KDTree::make_tree(std::vector<halftoneparticle::Particle>::iterator &part_begin,
                            std::vector<halftoneparticle::Particle>::iterator &part_end,
                            const pointIndexArr::iterator &begin,//
                            const pointIndexArr::iterator &end,  //
                            const size_t &length,                //
                            const size_t &level                  //
) {
    if (begin == end) {
        return NewKDNodePtr();// empty tree
    }

    size_t dim = 2;

    if (length > 1) {
        sort_on_idx(begin, end, level);
    }

    auto middle = begin + (length / 2);
    auto part_middle = part_begin + (length / 2);

    auto l_begin = begin;
    auto l_end = middle;
    auto r_begin = middle + 1;
    auto r_end = end;

    auto l_part_begin = part_begin;
    auto l_part_end = part_middle;
    auto r_part_begin = part_middle + 1;
    auto r_part_end = part_end;

    size_t l_len = length / 2;
    size_t r_len = length - l_len - 1;

    KDNodePtr left;
    if (l_len > 0 && dim > 0) {
        left = make_tree(l_part_begin, l_part_end, l_begin, l_end, l_len, (level + 1) % dim);
    } else {
        left = leaf;
    }
    KDNodePtr right;
    if (r_len > 0 && dim > 0) {
        right = make_tree(r_part_begin, r_part_end, r_begin, r_end, r_len, (level + 1) % dim);
    } else {
        right = leaf;
    }

    // KDNode result = KDNode();
    return std::make_shared<KDNode>(*part_middle, left, right);
}

KDTree::KDTree(std::vector<halftoneparticle::Particle> &particles) {
    //    pointVec point_array;
    //    for(const halftoneparticle::Particle& particle : particles) {
    //        point_array.push_back(std::vector<double>(particle.position().x,particle.position().y));
    //    }
    //TODO delete
    //std::pair<point_t , int> test(std::vector<double>(1,2),2);
    //    std::pair<point_t, halftoneparticle::Particle> test(std::vector<double>(1,2),halftoneparticle::Particle(glm::vec2(1,2), glm::vec2(1,2),.5f));
    //    halftoneparticle::Particle x = test.second;

    leaf = std::make_shared<KDNode>();
    // iterators
    pointIndexArr arr;
    for (size_t i = 0; i < particles.size(); i++) {
        particles.at(i).SetAge(i);
        double xcoor = particles.at(i).position().x;
        double ycoor = particles.at(i).position().y;
        std::vector<double> pos({xcoor, ycoor});
        arr.push_back(pointIndex(pos, i));
    }

    auto begin = arr.begin();
    auto end = arr.end();

    std::vector<halftoneparticle::Particle>::iterator part_begin = particles.begin();
    std::vector<halftoneparticle::Particle>::iterator part_end = particles.end();

    size_t length = arr.size();
    size_t level = 0;// starting

    root = KDTree::make_tree(part_begin, part_end, begin, end, length, level);
}

//KDNodePtr KDTree::nearest_(   //
//    const KDNodePtr &branch,  //
//    const point_t &pt,        //
//    const size_t &level,      //
//    const KDNodePtr &best,    //
//    const double &best_dist   //
//) {
//    double d, dx, dx2;
//
//    if (!bool(*branch)) {
//        return NewKDNodePtr();  // basically, null
//    }
//
//    point_t branch_pt(*branch);
//    size_t dim = branch_pt.size();
//
//    d = dist2(branch_pt, pt);
//    dx = branch_pt.at(level) - pt.at(level);
//    dx2 = dx * dx;
//
//    KDNodePtr best_l = best;
//    double best_dist_l = best_dist;
//
//    if (d < best_dist) {
//        best_dist_l = d;
//        best_l = branch;
//    }
//
//    size_t next_lv = (level + 1) % dim;
//    KDNodePtr section;
//    KDNodePtr other;
//
//    // select which branch makes sense to check
//    if (dx > 0) {
//        section = branch->left;
//        other = branch->right;
//    } else {
//        section = branch->right;
//        other = branch->left;
//    }
//
//    // keep nearest neighbor from further down the tree
//    KDNodePtr further = nearest_(section, pt, next_lv, best_l, best_dist_l);
//    if (!further->x.empty()) {
//        double dl = dist2(further->x, pt);
//        if (dl < best_dist_l) {
//            best_dist_l = dl;
//            best_l = further;
//        }
//    }
//    // only check the other branch if it makes sense to do so
//    if (dx2 < best_dist_l) {
//        further = nearest_(other, pt, next_lv, best_l, best_dist_l);
//        if (!further->x.empty()) {
//            double dl = dist2(further->x, pt);
//            if (dl < best_dist_l) {
//                best_dist_l = dl;
//                best_l = further;
//            }
//        }
//    }
//
//    return best_l;
//};

// default caller
//KDNodePtr KDTree::nearest_(const point_t &pt) {
//    size_t level = 0;
//    // KDNodePtr best = branch;
//    double branch_dist = dist2(point_t(*root), pt);
//    return nearest_(root,          // beginning of tree
//                    pt,            // point we are querying
//                    level,         // start from level 0
//                    root,          // best is the root
//                    branch_dist);  // best_dist = branch_dist
//};
//
//point_t KDTree::nearest_point(const point_t &pt) {
//    return point_t(*nearest_(pt));
//};
//size_t KDTree::nearest_index(const point_t &pt) {
//    return size_t(*nearest_(pt));
//};
//
//pointIndex KDTree::nearest_pointIndex(const point_t &pt) {
//    KDNodePtr Nearest = nearest_(pt);
//    return pointIndex(point_t(*Nearest), size_t(*Nearest));
//}

std::vector<halftoneparticle::Particle> KDTree::neighborhood_(//
        const KDNodePtr &branch,                              //
        const glm::vec2 &pt,                                  //
        const double &rad,                                    //
        const size_t &level                                   //
) {
    double d, dx, dx2;

    if (!bool(*branch)) {
        // branch has no point, means it is a leaf,
        // no points to add
        return std::vector<halftoneparticle::Particle>();
    }

    size_t dim = 2;

    double r2 = rad * rad;

    d = dist2(branch->particle_.position(), pt);
    dx = branch->particle_.position().x - pt.x;
    dx2 = dx * dx;

    std::vector<halftoneparticle::Particle> nbh, nbh_s, nbh_o;
    if (d <= rad) {
        nbh.push_back(std::move(branch->particle_));
    }

    //
    KDNodePtr section;
    KDNodePtr other;
    if (dx > 0) {
        section = branch->left;
        other = branch->right;
    } else {
        section = branch->right;
        other = branch->left;
    }

    nbh_s = neighborhood_(section, pt, rad, (level + 1) % dim);
    nbh.insert(nbh.end(), nbh_s.begin(), nbh_s.end());
    if (dx2 < r2) {
        nbh_o = neighborhood_(other, pt, rad, (level + 1) % dim);
        nbh.insert(nbh.end(), nbh_o.begin(), nbh_o.end());
    }

    return nbh;
};

std::vector<halftoneparticle::Particle> KDTree::neighborhood(//
        const halftoneparticle::Particle &p,                 //
        const double &rad) {
    size_t level = 0;
    //point_t pos = {p.position().x,p.position().y};
    return neighborhood_(root, p.position(), rad, level);
}

//pointVec KDTree::neighborhood_points(  //
//    const point_t &pt,                 //
//    const double &rad) {
//    size_t level = 0;
//    std::vector<halftoneparticle::Particle> nbh = neighborhood_(root, pt, rad, level);
//    pointVec nbhp;
//    nbhp.resize(nbh.size());
//    std::transform(nbh.begin(), nbh.end(), nbhp.begin(),
//                   [](pointIndex x) { return x.first; });
//    return nbhp;
//}

//indexArr KDTree::neighborhood_indices(  //
//    const point_t &pt,                  //
//    const double &rad) {
//    size_t level = 0;
//    std::vector<halftoneparticle::Particle> nbh = neighborhood_(root, pt, rad, level);
//    indexArr nbhi;
//    nbhi.resize(nbh.size());
//    std::transform(nbh.begin(), nbh.end(), nbhi.begin(),
//                   [](pointIndex x) { return x.second; });
//    return nbhi;
//}
