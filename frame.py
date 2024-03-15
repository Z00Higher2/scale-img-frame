import numpy as np

MAX_H = 512
MAX_W = 512

# Function to read the input image from a file
def read_image():
    with open("inImage.pgm", "r") as instr:
        # Read and validate the PGM file header
        assert instr.readline().strip() == 'P2'
        # Skip any comments in the file
        line = instr.readline().strip()
        while line.startswith('#'):
            line = instr.readline().strip()
        width, height = map(int, line.split())
        assert width <= MAX_W
        assert height <= MAX_H
        max_val = int(instr.readline().strip())
        assert max_val == 255

        # Read pixel values into the image array
        image = []
        for _ in range(height):
            row = list(map(int, instr.readline().split()))
            assert len(row) == width
            image.append(row)
        return np.array(image), height, width

# Function to write the output image to a file
def write_image(image):
    with open("outImage.pgm", "w") as ostr:
        # Write the PGM file header
        ostr.write("P2\n")
        ostr.write(f"{image.shape[1]} {image.shape[0]}\n")
        ostr.write("255\n")

        # Write pixel values to the output file
        for row in image:
            ostr.write(" ".join(map(str, row)) + "\n")

def main():
    # Read the input image from the file
    img, h, w = read_image()

    # Copy the input image to the output image
    out = np.copy(img)

    # Calculate dimensions and position of the 50/50 dimensional box
    box_width = w // 2
    box_height = h // 2
    box_start_x = (w - box_width) // 2
    box_start_y = (h - box_height) // 2

    # Perform the image processing (creating the outer frame)
    out[box_start_y:box_start_y + box_height, box_start_x] = 255
    out[box_start_y:box_start_y + box_height, box_start_x + box_width - 1] = 255
    out[box_start_y, box_start_x:box_start_x + box_width] = 255
    out[box_start_y + box_height - 1, box_start_x:box_start_x + box_width] = 255

    # Calculate dimensions and position of the inner box
    inner_box_width = box_width - 2
    inner_box_height = box_height - 2
    inner_box_start_x = box_start_x + 1
    inner_box_start_y = box_start_y + 1

    # Perform the image processing (creating the inner box)
    out[inner_box_start_y:inner_box_start_y + inner_box_height, inner_box_start_x:inner_box_start_x + inner_box_width] = img[inner_box_start_y:inner_box_start_y + inner_box_height, inner_box_start_x:inner_box_start_x + inner_box_width]

    # Write the processed image to the output file
    write_image(out)

if __name__ == "__main__":
    main()
