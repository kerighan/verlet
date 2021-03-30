from verlet import Universe, Node, Charge
import numpy as np
import svgwrite

factor= 40

volumes = {
    "art": 130,
    "food": 372,
    "environment": 899,
    "tech": 172,
    "fashion": 74.5,
    "health": 514,
    "urbanism": 68.5
}

colors = {
    "art": "#8c5f4c",
    "food": "#f16767",
    "environment": "#0bb578",
    "tech": "#f3a734",
    "fashion": "#3ca0e9",
    "health": "#0b1cb5",
    "urbanism": "#6123c5"
}
keys = list(volumes)

charge = Charge(50, 50, 2)
nodes = []
for key in keys:
    value = volumes[key]
    x, y = np.random.normal(size=2, loc=50, scale=10)
    node = Node(x, y, value / factor, m=value, friction=0.1)
    charge.add(node)
    nodes.append(node)


universe = Universe(.1)
universe.add_nodes(nodes)
universe.add_forces([charge])
positions = universe.history(200)

# svgwrite
dwg = svgwrite.Drawing('test.svg', width=1000, height=1000)
i = 0
for node, key in zip(nodes, keys):
    radius = volumes[key]
    x, y = positions[-1, i]
    x *= 1000 / 100
    y *= 1000 / 100
    radius *= 1000 / 100
    radius *= 0.9
    circle = dwg.circle((x, y), radius / factor, stroke=colors[key], stroke_width=3, fill_opacity=0)
    dwg.add(circle)
    i += 1
dwg.save()
