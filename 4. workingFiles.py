with open("input.txt", "r") as input_file, open("output.txt", "w") as output_file:
    lines = input_file.readlines()
    output_file.writelines(lines[1::2])
