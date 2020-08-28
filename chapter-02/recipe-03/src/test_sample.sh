#!/usr/bin/env bash

echo "./sample_unweight_graph_dfs_iter_dot1 dfs_init.dot dfs.dot"
./sample_unweight_graph_dfs_iter_dot1 dfs_init.dot dfs.dot
dot dfs_init.dot -T png -o dfs_init.png
dot dfs.dot -T png -o dfs.png

