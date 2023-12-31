import heapq

class Vertex:
    def __init__(self, name):
        self.name = name
        self.neighbors = {}
    
    def add_neighbor(self, neighbor, weight):
        self.neighbors[neighbor] = weight

class Graph:
    def __init__(self):
        self.vertices = {}
    
    def add_vertex(self, vertex):
        self.vertices[vertex.name] = vertex
    
    def get_vertex(self, name):
        return self.vertices[name]
    
    def get_vertices(self):
        return self.vertices.values()

class RoutingTable:
    def __init__(self, destination):
        self.destination = destination
        self.previous_vertex = None
        self.distance = float('inf')

class DijkstraAlgorithm:
    def __init__(self, graph):
        self.graph = graph
    
    def dijkstra(self, start_vertex_name):
        start_vertex = self.graph.get_vertex(start_vertex_name)
        start_vertex.routing_table = RoutingTable(start_vertex_name)
        start_vertex.routing_table.distance = 0
        
        priority_queue = [(0, start_vertex)]
        
        while priority_queue:
            current_distance, current_vertex = heapq.heappop(priority_queue)
            
            if current_distance > current_vertex.routing_table.distance:
                continue
            
            for neighbor, weight in current_vertex.neighbors.items():
                distance = current_distance + weight
                
                if distance < neighbor.routing_table.distance:
                    neighbor.routing_table.distance = distance
                    neighbor.routing_table.previous_vertex = current_vertex
                    
                    heapq.heappush(priority_queue, (distance, neighbor))

class AStarAlgorithm:
    def __init__(self, graph, heuristic):
        self.graph = graph
        self.heuristic = heuristic
    
    def astar(self, start_vertex_name, goal_vertex_name):
        start_vertex = self.graph.get_vertex(start_vertex_name)
        start_vertex.routing_table = RoutingTable(start_vertex_name)
        start_vertex.routing_table.distance = 0
        
        priority_queue = [(0 + self.heuristic(start_vertex_name, goal_vertex_name), start_vertex)]
        
        while priority_queue:
            current_distance, current_vertex = heapq.heappop(priority_queue)
            
            if current_distance > current_vertex.routing_table.distance:
                continue
            
            if current_vertex.name == goal_vertex_name:
                break
            
            for neighbor, weight in current_vertex.neighbors.items():
                distance = current_vertex.routing_table.distance + weight
                
                if distance < neighbor.routing_table.distance:
                    neighbor.routing_table.distance = distance
                    neighbor.routing_table.previous_vertex = current_vertex
                    
                    priority = distance + self.heuristic(neighbor.name, goal_vertex_name)
                    heapq.heappush(priority_queue, (priority, neighbor))

# Example usage:
# Create vertices
a = Vertex('A')
b = Vertex('B')
c = Vertex('C')
d = Vertex('D')
e = Vertex('E')

# Add edges
a.add_neighbor(b, 4)
a.add_neighbor(c, 2)
b.add_neighbor(d, 5)
c.add_neighbor(b, 1)
c.add_neighbor(d, 8)
c.add_neighbor(e, 10)
d.add_neighbor(e, 2)

# Create graph
graph = Graph()
graph.add_vertex(a)
graph.add_vertex(b)
graph.add_vertex(c)
graph.add_vertex(d)
graph.add_vertex(e)

# Create Dijkstra algorithm instance
dijkstra = DijkstraAlgorithm(graph)

# Run Dijkstra algorithm
dijkstra.dijkstra('A')

# Print shortest paths
for vertex in graph.get_vertices():
    print(f"Shortest path to vertex {vertex.name}:")
    current_vertex = vertex
    while current_vertex:
        print(current_vertex.name)
        current_vertex = current_vertex.routing_table.previous_vertex

# Create A* algorithm instance
def heuristic(source, destination):
    # Example heuristic function (Euclidean distance between vertices)
    source_vertex = graph.get_vertex(source)
    destination_vertex = graph.get_vertex(destination)
    return ((source_vertex.x - destination_vertex.x) ** 2 + (source_vertex.y - destination_vertex.y) ** 2) ** 0.5

astar = AStarAlgorithm(graph, heuristic)

# Run A* algorithm
astar.astar('A', 'E')

# Print shortest path
print("Shortest path from A to E:")
current_vertex = graph.get_vertex('E')
while current_vertex:
    print(current_vertex.name)
    current_vertex = current_vertex.routing_table.previous_vertex