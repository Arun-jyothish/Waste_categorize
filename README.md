# Waste_categorize

~~~mermaid
graph TD 
A((START)) --> B{CHECK ULTRASONIC_READING}
E-->D1[DELAY]
B--BELOW_THRESHOLD-->E[/OPEN EXT LID/]
D1-->FL[SET FLAG]
FL-->STOP((END))
B --ABOVE_THRESHOLD-->D[/CLOSE EXT LID/]
D-->CH{CHECK METAL}
CH--YES-->Z1[DISTRIBUTOR TO METAL BIN]
CH--NO-->Z2{CHECK WEATHER WET OR NOT}
Z2--WET-->Z3[DISTRIBUTOR TO WET BIN]
Z2--DRY-->Z4[DISTRIBUTOR TO DRY BIN]
Z4-->DL{DELAY TS}
Z3-->DL
Z1-->DL
DL--FLAG NOT SET-->STOP
DL--FLAG SET-->INT[/INTERNAL LID OPEN/]
INT-->DL2[DELAY DUMP TIME]
DL2-->CL2[/CLOSE INT LID/]
CL2-->FL2[UNSET FLAG]
FL2-->STOP

~~~