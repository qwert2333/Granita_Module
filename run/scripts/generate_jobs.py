import os

pitch = [15, 10, 7, 5, 3]  # GeV
numfiber = [26, 40, 56, 80, 132]
nevents = 10000

os.makedirs("../macros", exist_ok=True)

with open("macro_list.txt", "w") as f:
    for i in range(len(pitch)):
        macro_name = f"../macros/run_pitch{pitch[i]}_1GeV.mac"

        with open(macro_name, "w") as m:
            m.write(f"""
/random/setSeeds 123456 789012

/run/numberOfThreads 4

/run/setCut 0.1 mm

/run/verbose 1
/event/verbose 0
/tracking/verbose 0

# Detector construction
/detector/pitchSize {pitch[i]} mm
/detector/fiberNum {numfiber[i]}
/detector/ZSegNum 25

/run/initialize

# Set particle gun
/gps/particle gamma
/gps/energy 1 GeV
/gps/direction 0 0 1
/gps/pos/type Plane
/gps/pos/shape Square
/gps/pos/centre 0 0 -50 cm
/gps/pos/halfx 2.5 cm
/gps/pos/halfy 2.5 cm


# Run event number
/run/beamOn {nevents}
""")

        f.write(f"{macro_name}\n")
