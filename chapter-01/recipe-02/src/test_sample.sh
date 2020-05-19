#!/usr/bin/env bash

echo "./sample_unweight_dense_graph1"
./sample_unweight_dense_graph1

echo
echo

echo "./sample_unweight_dense_graph2 unweight_dense_graph2.dot"
./sample_unweight_dense_graph2 unweight_dense_graph2.dot
dot unweight_dense_graph2.dot -T png -o unweight_dense_graph2.png
echo "output png is unweight_dense_graph2.png"
