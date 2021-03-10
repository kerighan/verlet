from verlet import Node, Charge, Universe

node = Node(1, 1, 1)

charge = Charge(0, 0, 1)
charge.add(node)

universe = Universe(1)
universe.add_nodes([node])
universe.add_force(charge)

for i in range(10):
    universe.run()
