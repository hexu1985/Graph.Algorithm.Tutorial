#!/usr/bin/env bash

echo "./sample_unweight_digraph_topo_sort_dot1 topo_sort_init.dot topo_sort.dot"
./sample_unweight_digraph_topo_sort_dot1 topo_sort_init.dot topo_sort.dot
dot topo_sort_init.dot -T png -o topo_sort_init.png
dot topo_sort.dot -T png -o topo_sort.png

