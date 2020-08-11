#!/usr/bin/env bash

echo "./sample_unweight_graph_bfs_dot1 bfs_init.dot bfs.dot"
./sample_unweight_graph_bfs_dot1 bfs_init.dot bfs.dot
dot bfs_init.dot -T png -o bfs_init.png
dot bfs.dot -T png -o bfs.png

