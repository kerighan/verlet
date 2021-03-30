from verlet import Universe, Node, Link

# ping()

node = Node(10, 10, 1, friction=.1)
node_2 = Node(20, 20, 1, friction=.1)
link = Link(node, node_2, 1)


universe = Universe(.1)
universe.add_nodes([node, node_2])
universe.add_forces([link])
positions = universe.history(100)
print(positions)
