#!/usr/bin/env bash

echo "./sample_unweight_dense_graph1"
./sample_unweight_dense_graph1

echo
echo

echo "./sample_unweight_dense_graph2 unweight_dense_graph2.dot"
./sample_unweight_dense_graph2 unweight_dense_graph2.dot
dot unweight_dense_graph2.dot -T png -o unweight_dense_graph2.png
echo "output png is unweight_dense_graph2.png"

echo "./sample_unweight_dense_graph_dot1 unweight_dense_graph_dot1.dot"
./sample_unweight_dense_graph_dot1 unweight_dense_graph_dot1.dot 
dot unweight_dense_graph_dot1.dot -T png -o unweight_dense_graph_dot1.png
echo "output png is unweight_dense_graph_dot1.png"

echo
echo

echo "./sample_unweight_dense_digraph1"
./sample_unweight_dense_digraph1

echo
echo

echo "./sample_unweight_dense_digraph2 unweight_dense_digraph2.dot"
./sample_unweight_dense_digraph2 unweight_dense_digraph2.dot
dot unweight_dense_digraph2.dot -T png -o unweight_dense_digraph2.png
echo "output png is unweight_dense_digraph2.png"
