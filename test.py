from verlet import Node, Charge, Universe
import numpy as np
import random
import time


def draw(positions, nodes, fps=15):
    from cmotion import Scene
    from cmotion.shape import Circle
    from cmotion.animation import Timeline
    import numpy as np

    positions = positions.transpose((1, 0, 2))
    scene = Scene(1000, 1000)

    duration = 4
    keyframes = np.linspace(0, duration, positions.shape[1])
    timelines = []
    for i, pos in enumerate(positions):
        r = nodes[i].get_radius()
        circle = Circle(radius=r, color="#1DA1F2", z_index=i)

        timeline = Timeline(keyframes)
        for j in range(1, pos.shape[0]):
            x, y = pos[j]
            x_b, y_b = pos[j - 1]
            timeline.linear("x", x_b, x)
            timeline.linear("y", y_b, y)
        timelines.append(timeline)
        circle.add(timeline)
        scene.add(circle)

    keyframes = np.linspace(0, duration, 5 * duration)
    for i, t in enumerate(keyframes):
        # scene.save(f"render/{i}.jpg", t)
        scene.to_svg(f"svg/{i}.svg", t)

    # scene.render("render", fps=30)
    # scene.save("render.jpg", 2)


charge = Charge(50, 50, 1)
nodes = []
for i in range(100):
    x = (random.random() - .5) * 100 + 50
    y = (random.random() - .5) * 100 + 50
    r = 3 * random.random()**3 + .1
    node = Node(x, y, r, m=r, friction=0.1)
    charge.add(node)
    nodes.append(node)


universe = Universe(.1)
universe.add_nodes(nodes)
universe.add_forces([charge])
positions = universe.history(100)

start = time.time()
draw(positions, nodes)
print(time.time() - start)
