#!/usr/bin/env bash

echo "./sample_unweight_sparse_multi_graph1"
./sample_unweight_sparse_multi_graph1

echo
echo

echo "./sample_unweight_sparse_multi_graph2 unweight_sparse_multi_graph2.dot"
./sample_unweight_sparse_multi_graph2 unweight_sparse_multi_graph2.dot
dot unweight_sparse_multi_graph2.dot -T png -o unweight_sparse_multi_graph2.png
echo "output png is unweight_sparse_multi_graph2.png"

echo

echo "./sample_unweight_sparse_multi_digraph1"
./sample_unweight_sparse_multi_digraph1

echo
echo

echo "./sample_unweight_sparse_multi_digraph2 unweight_sparse_multi_digraph2.dot"
./sample_unweight_sparse_multi_digraph2 unweight_sparse_multi_digraph2.dot
dot unweight_sparse_multi_digraph2.dot -T png -o unweight_sparse_multi_digraph2.png
echo "output png is unweight_sparse_multi_digraph2.png"
