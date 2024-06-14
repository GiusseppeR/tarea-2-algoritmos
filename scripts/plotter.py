import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import json
import sys
from matplotlib.lines import Line2D

def plot_times(nodes, n_edges, times_heap, times_fq, filename):
    plt.figure(figsize=(8, 6))
    
    plt.plot(n_edges, times_heap, label='Heap', marker='o', linestyle='-')
    plt.plot(n_edges, times_fq, label='Fibonacci Queue', marker='o', linestyle='-')
    
    slope_heap, intercept_heap = np.polyfit(n_edges, times_heap, 1)
    regression_line_heap = np.array(n_edges) * slope_heap + intercept_heap
    plt.plot(n_edges, regression_line_heap, label='Heap Regression Line', linestyle='--')
    
    slope_fq, intercept_fq = np.polyfit(n_edges, times_fq, 1)
    regression_line_fq = np.array(n_edges) * slope_fq + intercept_fq
    plt.plot(n_edges, regression_line_fq, label='Fibonacci Queue Regression Line', linestyle='--')
    
    plt.xlabel('Number of edges')
    plt.ylabel('Execution Time [s]')
    plt.title(f'Execution times for {nodes} nodes')
    plt.legend()
    plt.grid(True)
    plt.savefig(filename)

def plot_graph(adjacency_matrix, mst):
    nodes = len(mst)
    T = np.zeros((nodes,nodes))
    for i in range(nodes):
        if i == 0:
            continue
        T[i][mst[i]] = adjacency_matrix[i][mst[i]]
        T[mst[i],i] = adjacency_matrix[i][mst[i]]

    sG = nx.from_numpy_array(T)
    G = nx.from_numpy_array(adjacency_matrix)
    pos = nx.spring_layout(G)

    sG_edges = sG.edges()
    plt.figure(figsize=(8, 6))
    nx.draw(G, pos, with_labels=True, node_color='black', edge_color='gray', node_size=10, font_size=1)
    nx.draw_networkx_edges(G, pos, edgelist=sG_edges, edge_color='red')
    plt.title('Graph Visualization from Adjacency Matrix')

    legend_elements = [Line2D([0], [0], color='grey', lw=2, label='Full Graph Edges'),
                   Line2D([0], [0], color='red', lw=2, label='Dijkstra MST Edges')]
    plt.legend(handles=legend_elements)

    plt.savefig("graph.pdf")

def main():
    with open(sys.argv[1], "r") as file:
        data = json.load(file)

    graph = []
    graph_rows = data["example_graph"].split(";")
    for row in graph_rows:
        l = np.array([float(x) for x in row.split(",")])
        graph.append(l);
    mst = [int(x) for x in data["example_mst"].split("+")]
    graph = np.array(graph)
    plot_graph(graph,mst)

    node_amounts = [int(x) for x in data["input_sizes"].split("+")]
    edge_amounts = [int(x) for x in data["edges"].split("+")]
    heap_times = [float(x) for x in data["heap_mean_times"].split("+")]
    fq_times = [float(x) for x in data["fq_mean_times"].split("+")]
    
    for i in range(len(node_amounts)):
        if i == 0:
            plot_times(node_amounts[i], edge_amounts[:3], heap_times[:3], fq_times[:3], f"times_{i}.pdf")
        else:
            start_index = 3 + (i - 1) * 7
            end_index = start_index + 7
            plot_times(node_amounts[i], edge_amounts[start_index:end_index], heap_times[start_index:end_index], fq_times[start_index:end_index], f"times_{i}.pdf")


if __name__ == "__main__":
    main()
