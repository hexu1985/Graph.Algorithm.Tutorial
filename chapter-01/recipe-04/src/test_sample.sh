#!/usr/bin/env bash

echo "./sample_weight_dense_graph1"
./sample_weight_dense_graph1

echo
echo

echo "./sample_weight_dense_graph2 weight_dense_graph2.dot"
./sample_weight_dense_graph2 weight_dense_graph2.dot
dot weight_dense_graph2.dot -T png -o weight_dense_graph2.png
echo "output png is weight_dense_graph2.png"

echo

echo "./sample_weight_dense_digraph1"
./sample_weight_dense_digraph1

echo
echo

echo "./sample_weight_dense_digraph2 weight_dense_digraph2.dot"
./sample_weight_dense_digraph2 weight_dense_digraph2.dot
dot weight_dense_digraph2.dot -T png -o weight_dense_digraph2.png
echo "output png is weight_dense_digraph2.png"
