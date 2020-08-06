#!/usr/bin/env bash

echo "./sample_unweight_graph_bfs_dot1 init.dot bfs.dot"
./sample_unweight_graph_bfs_dot1 init.dot bfs.dot
dot init.dot -T png -o init.png
dot bfs.dot -T png -o bfs.png
