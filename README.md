# Waste_categorize

~~~mermaid
graph TD 
a[start] --> b{check ultrasonic_reading}
e-->d1[delay]
b--below_value-->e[open ext lid]
b --above_value-->d[close ext lid]
d-->ch{check metal}
ch--yes-->z1[distributor go to metal bin]
ch--no-->z2{check weather wet or not}
z2--wet-->z3[distributor go to wet bin]
z2--dry-->z4[distributor go to dry bin]
z4-->dl[delay ts]
z3-->dl
z1-->dl
dl-->int[internal lid open]
int-->dl2[delay dump time]
dl2-->cl2[close int lid]
cl2-->a

~~~