import cairosvg

names = ["book-solid", "gear-solid", "palette-solid", "ranking-star-solid", "user-regular"]
for name in names:  
    svg = name + ".svg"
    png = name + ".png"
    cairosvg.svg2png(url=svg, write_to=png)