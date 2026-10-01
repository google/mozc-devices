# Build Guide

![Gboard DIY](./images/diy.webp)

[Overview of the project](./README.md)

## File List

- `stls/` : 3D model files (STL) for the case and mechanisms
- [`board/`](./board/README.md) : Documentation for electronics and wiring (Coming soon)
- [`firmware/`](./firmware/README.md) : Firmware development resources
- `firmware/prebuilt/` : Pre-built firmware binaries

## Editions

There are two editions of this keyboard:
- **Moving Keys Edition**: A motorized conveyor belt edition where the keys physically circulate.
- **Bluetooth Connection Edition**: A functional Bluetooth keyboard edition (Coming soon).

The instructions below describe how to build the **Moving Keys Edition**.

## Moving Keys Edition

### Bill of Materials (BOM)

#### 3D Printed Parts

| Preview | Part Name | File | Qty | Notes |
| :-: | :--- | :--- | :-: | :--- |
| ![Base_Roller](./images/previews/Base_Roller.svg) | Base_Roller | [`Base_Roller.stl`](./stls/Base_Roller.stl) | 2 | Base roller |
| ![Base_Side](./images/previews/Base_Side.svg) | Base_Side | [`Base_Side.stl`](./stls/Base_Side.stl) | 2 | Base side frame (L/R) |
| ![BaseCoverL](./images/previews/BaseCoverL.svg) | BaseCoverL | [`BaseCoverL.stl`](./stls/BaseCoverL.stl) | 1 | Base left cover |
| ![BaseCoverR](./images/previews/BaseCoverR.svg) | BaseCoverR | [`BaseCoverR.stl`](./stls/BaseCoverR.stl) | 1 | Base right cover |
| ![BottomTube](./images/previews/BottomTube.svg) | BottomTube | [`BottomTube.stl`](./stls/BottomTube.stl) | 3 | OD 21mm / ID 18mm / L 70mm pipe can also be used |
| ![BottomTubePlate](./images/previews/BottomTubePlate.svg) | BottomTubePlate | [`BottomTubePlate.stl`](./stls/BottomTubePlate.stl) | 1 | Bottom tube support plate |
| ![Box](./images/previews/Box.svg) | Box | [`Box.stl`](./stls/Box.stl) | 1 | Main enclosure box |
| ![Cover_BottomL](./images/previews/Cover_BottomL.svg) | Cover_BottomL | [`Cover_BottomL.stl`](./stls/Cover_BottomL.stl) | 1 | Lower left cover |
| ![Cover_Top](./images/previews/Cover_Top.svg) | Cover_Top | [`Cover_Top.stl`](./stls/Cover_Top.stl) | 2 | Upper side cover (common for L/R) |
| ![Cover_wAtom](./images/previews/Cover_wAtom.svg) | Cover_wAtom | [`Cover_wAtom.stl`](./stls/Cover_wAtom.stl) | 1 | Lower side cover with slot for ATOMS3 Lite |
| ![MotorSupport](./images/previews/MotorSupport.svg) | MotorSupport | [`MotorSupport.stl`](./stls/MotorSupport.stl) | 1 | Motor and driver support bracket |
| ![SidePlate_Bottom](./images/previews/SidePlate_Bottom.svg) | SidePlate_Bottom | [`SidePlate_Bottom.stl`](./stls/SidePlate_Bottom.stl) | 2 | Lower inner side plate |
| ![SidePlate_Top](./images/previews/SidePlate_Top.svg) | SidePlate_Top | [`SidePlate_Top.stl`](./stls/SidePlate_Top.stl) | 2 | Upper inner side plate |
| ![SprocketA](./images/previews/SprocketA.svg) | SprocketA | [`SprocketA.stl`](./stls/SprocketA.stl) | 4 | Sprocket A (protrusions on one side only) |
| ![SprocketB](./images/previews/SprocketB.svg) | SprocketB | [`SprocketB.stl`](./stls/SprocketB.stl) | 6 | Sprocket B (protrusions on both sides at the same angle) |
| ![SprocketC](./images/previews/SprocketC.svg) | SprocketC | [`SprocketC.stl`](./stls/SprocketC.stl) | 6 | Sprocket C (protrusions on both sides at offset angles) |
| ![Stay](./images/previews/Stay.svg) | Stay | [`Stay.stl`](./stls/Stay.stl) | 2 | t2mm 12×110mm |
| ![Belt](./images/previews/Belt.svg) | Belt | [`Belt.stl`](./stls/Belt.stl) | 116 | Conveyor belt link (29 pcs × 4 columns) |

#### Mechanical Parts & Fasteners

| Part Name | Qty | Notes / Reference Links |
| :--- | :-: | :--- |
| 3mm L105mm Shaft | 2 | [Reference](https://www.amazon.co.jp/dp/B0DS8YLN65) (Cut to 105mm) |
| Insert Nut M4 x 4mm x 5mm | 14 | [Reference 1](https://www.amazon.co.jp/dp/B0DJ8C9PJN) / [Reference 2](https://www.amazon.co.jp/dp/B0FFGZKGJC) |
| Insert Nut M2.5 x 3.5mm x 3.5mm | 8 | [Reference](https://www.amazon.co.jp/dp/B0FVD9XB56) |
| Hex Socket Set Screw M2.5 x 4mm | 4 | [Reference](https://www.amazon.co.jp/dp/B0F4Q98MY7) |
| Hex Socket Head Cap Screw M4 x 8mm | 12 | [Reference](https://www.amazon.co.jp/dp/B0DDWLZYRK) |
| Hex Socket Head Cap Screw M4 x 6mm | 2 | [Reference](https://www.amazon.co.jp/dp/B002A5KK76) |
| Hex Socket Head Cap Screw M2.5 x 8mm | 4 | [Reference](https://www.amazon.co.jp/dp/B0FLYCZ4R2) |
| Timing Pulley 2GT (6mm belt width, 20T, 3mm bore) | 2 | [Reference](https://www.amazon.co.jp/dp/B09Y1N3WXT) |
| Timing Belt 2GT (6mm width, 110mm length) | 1 | [Reference](https://www.amazon.co.jp/dp/B0CNT721G6) |
| Bearing 623ZZ (ID 3mm, OD 10mm, W 4mm) | 4 | [Reference](https://www.amazon.co.jp/dp/B0G6ZG3Z8F) |
| Bearing MR63ZZ (ID 3mm, OD 6mm, W 2.5mm) | 1 | [Reference](https://www.amazon.co.jp/dp/B0CFZQRL8C) |
| 3mm Shaft Collar (OD 8mm, W 4mm) | 3 | [Reference](https://www.amazon.co.jp/dp/B0CQNYN2N6) |

#### Electronic Parts

| Part Name | Qty | Notes / Reference Links |
| :--- | :-: | :--- |
| Motor Driver DRV8833 | 1 | [Reference](https://www.amazon.co.jp/dp/B098Q24ZV9) |
| DC6V N20 Metal Gear Motor (3mm shaft, 150RPM) | 1 | [Reference](https://www.amazon.co.jp/dp/B0FZFKGC6F) |
| ATOMS3 Lite | 1 | [Reference](https://www.switch-science.com/products/8778) |
| 2.54mm Pin Header 4P | 1 | [Reference](https://www.amazon.co.jp/dp/B0829W3T8Q) |
| 2.54mm Pin Header 5P | 1 | |
| 220μF Electrolytic Capacitor | 1 | [Reference](https://www.amazon.co.jp/dp/B07D3P2NFY) |
| 0.1μF Ceramic Capacitor | 1 | [Reference](https://www.amazon.co.jp/dp/B079YJ78VS) |
| Kailh Low Profile Switch (Choc V1) | 116 | [Reference](https://shop.yushakobo.jp/collections/all-switches/products/pg1350) |
| Kailh Low Profile Keycap (Choc V1) | 116 | [Reference](https://shop.yushakobo.jp/collections/choc-v1-keycaps/products/pg1350cap-blank) |

### Assembly

#### Step 1: Prepare 3D-Printed Parts and Install Insert Nuts

1. Print all 18 types of 3D-printed parts (157 pieces in total) listed in the BOM above. Note that `BottomTube` (3 pcs) can also be substituted with an off-the-shelf pipe (OD 21mm, ID 18mm, length 70mm).
2. Using a soldering iron, press the M4 heat-set insert nuts (14 pcs) into `Base_Side` (1 pc × 2), `Base_Roller` (2 pcs × 2), and `Box` (4 pcs × 2).

![M4 Insert Nuts](./images/insert_nut.webp)

3. Press the M2.5 heat-set insert nuts (8 pcs) into `MotorSupport` (2 pcs), `BottomTubePlate` (2 pcs), and the side of the boss on `SprocketA` (1 pc × 4).

![M2.5 Insert Nuts](./images/insert_nut2.webp)

#### Step 2: Assemble the Base

1. Attach the DC6V N20 metal gear motor (150RPM) and the `DRV8833` motor driver module to `MotorSupport`.
2. Assemble the base section by combining `BottomTube` (3 pcs), `Base_Roller` (2 pcs), `Base_Side` (2 pcs), `BottomTubePlate` (1 pc), and `MotorSupport` (1 pc), and secure them with M4 hex socket head cap screws. Route the power cable through the hole in `BottomTubePlate` and inside `BottomTube`.

![Base Assembly](./images/base.webp)

#### Step 3: Assemble Shafts and Sprockets

1. Onto each of the two 3mm shafts (105mm length), slide the sprockets in the order **`SprocketA`, `SprocketB`, `SprocketC`, `SprocketB`, `SprocketC`, `SprocketB`, `SprocketC`, `SprocketA`** (8 sprockets per shaft, 16 in total), and slide `623ZZ` bearings onto both ends of each shaft (4 pcs in total). Secure both ends of one shaft and one end of the other shaft using the 3mm shaft collars (3 pcs in total).
2. Secure `SprocketA` to the shafts using the M2.5 × 4mm hex socket set screws (4 pcs).

![Sprocket and Roller Assembly](./images/roller.webp)

#### Step 4: Assemble Frame and Drive Mechanism

1. Place the main `Box` enclosure in the center and fasten `SidePlate_Bottom`, `SidePlate_Top`, and the reinforcing `Stay` plates (2 pcs) using the hex socket head cap screws (M4 × 8mm, M4 × 6mm, and M2.5 × 8mm), clamping the shafts between the side plates.
2. Attach the 2GT timing pulleys (20T, 2 pcs in total) onto the 3mm shaft of the motor and the remaining end of the drive shaft (the end without a shaft collar).
3. Loop the 2GT timing belt (6mm width, 110mm length) around the motor pulley and the drive shaft pulley.
4. Connect the conveyor belt links `Belt` (29 pcs × 4 columns = 116 pcs) into 4 loops, mount the low-profile switches and keycaps onto them, and wrap the belt assemblies around the rollers.

![Frame and Drive Mechanism Assembly](./images/entire.webp)

#### Step 5: Mount the Electronics

1. Mount the `ATOMS3 Lite` controller into the dedicated slot on `Cover_wAtom`, and wire it to the `DRV8833` driver and capacitors (220μF electrolytic capacitor and 0.1μF ceramic capacitor).

#### Step 6: Attach Outer Covers

1. Attach the outer covers (`BaseCoverL`, `BaseCoverR`, `Cover_BottomL`, `Cover_wAtom`, and `Cover_Top` × 2) to the sides and secure them with screws to complete the assembly.

## Bluetooth Connection Edition

Coming soon.
