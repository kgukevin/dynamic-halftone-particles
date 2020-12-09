#pragma once

/*
 * file: KDTree.hpp
 * author: J. Frederico Carvalho
 *
 * This is an adaptation of the KD-tree implementation in rosetta code
 *  https://rosettacode.org/wiki/K-d_tree
 * It is a reimplementation of the C code using C++.
 * It also includes a few more queries than the original
 *
 */

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include "particle.h"

using point_t = std::vector< double >; // vector of points
using indexArr = std::vector< size_t >; // vector of corresponding indexes
using pointIndex = typename std::pair< std::vector< double >, size_t >; // combined vector and index

class KDNode {
   public:
    using KDNodePtr = std::shared_ptr< KDNode >;
    halftoneparticle::Particle particle_;
    size_t index;
    point_t x;
    KDNodePtr left;
    KDNodePtr right;

    // initializer
    KDNode();
    KDNode(const halftoneparticle::Particle &, const size_t &, const KDNodePtr &,
           const KDNodePtr &);
    KDNode(const halftoneparticle::Particle &, const pointIndex &, const KDNodePtr &, const KDNodePtr &);
    ~KDNode();

    // getter
    double coord(const size_t &);
    // halftoneparticle::Particle GetParticle();

    // conversions
    explicit operator bool();
    explicit operator point_t();
    explicit operator size_t();
    explicit operator pointIndex();
};

using KDNodePtr = std::shared_ptr< KDNode >;

KDNodePtr NewKDNodePtr();

// square euclidean distance
inline double dist2(const point_t &, const point_t &);
inline double dist2(const KDNodePtr &, const KDNodePtr &);

// euclidean distance
inline double dist(const point_t &, const point_t &);
inline double dist(const KDNodePtr &, const KDNodePtr &);

// Need for sorting
class comparer {
   public:
    size_t idx;
    explicit comparer(size_t idx_);
    inline bool compare_idx(
        const std::pair< std::vector< double >, size_t > &,  //
        const std::pair< std::vector< double >, size_t > &   //
    );
};

using pointIndexArr = typename std::vector< pointIndex >;

inline void sort_on_idx(const pointIndexArr::iterator &,  //
                        const pointIndexArr::iterator &,  //
                        size_t idx);

using pointVec = std::vector< point_t >;

class KDTree {
    KDNodePtr root;
    KDNodePtr leaf;

    KDNodePtr make_tree( const std::vector<halftoneparticle::Particle>::const_iterator &part_begin,
                         const std::vector<halftoneparticle::Particle>::const_iterator &part_end,
                         const pointIndexArr::iterator &begin,  //
                        const pointIndexArr::iterator &end,    //
                        const size_t &length,                  //
                        const size_t &level                    //
    );

   public:
    KDTree() = default;
    explicit KDTree(const std::vector<halftoneparticle::Particle>& particles);

   private:

    KDNodePtr nearest_(           //
        const KDNodePtr &branch,  //
        const point_t &pt,        //
        const size_t &level,      //
        const KDNodePtr &best,    //
        const double &best_dist   //
    );

    // default caller
    KDNodePtr nearest_(const point_t &pt);

   public:
    point_t nearest_point(const point_t &pt);
    size_t nearest_index(const point_t &pt);
    pointIndex nearest_pointIndex(const point_t &pt);

   private:
    std::vector<halftoneparticle::Particle> neighborhood_(  //
        const KDNodePtr &branch,  //
        const point_t &pt,        //
        const double &rad,        //
        const size_t &level       //
    );

   public:
    std::vector<halftoneparticle::Particle> neighborhood(  //
        const halftoneparticle::Particle &p,       //
        const double &rad);

//    pointVec neighborhood_points(  //
//        const point_t &pt,         //
//        const double &rad);

//    indexArr neighborhood_indices(  //
//        const point_t &pt,          //
//        const double &rad);
};
