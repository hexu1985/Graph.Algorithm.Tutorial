#!/usr/bin/env bash

echo "./sample_unweight_graph_bfs_dot1 bfs_init.dot bfs.dot"
./sample_unweight_graph_bfs_dot1 bfs_init.dot bfs.dot
dot bfs_init.dot -T png -o bfs_init.png
dot bfs.dot -T png -o bfs.png

echo
echo

echo "./sample_unweight_graph_ucc_dot1 ucc_init.dot ucc.dot"
./sample_unweight_graph_ucc_dot1 ucc_init.dot ucc.dot
dot ucc_init.dot -T png -o ucc_init.png
dot ucc.dot -T png -o ucc.png

