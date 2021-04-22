---
weight: 30
---

# Examples

To draw a 100x100 square:

{{< tabs "square" >}}
{{< tab "Python" >}}
```python3
# square.py

x = 50
y = 50
for i in range(100):
    for j in range(100):
        print(f"PX {x + i} {y + j} ff0000")
```

To draw the square, run the program and pipe it into netcat:

    $ python3 square.py | nc pixelflut.jedevc.com 1337
{{< /tab >}}
{{< /tabs >}}
