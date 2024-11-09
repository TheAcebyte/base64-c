# Base64 Encoder/Decoder in C
## About
This repository features a **Base64** encoder and decoder written in pure C.

## Base64
### What is Base64?
Base64 is an encoding scheme that converts arbitrary binary data to printable ASCII text.

### Why is it used?
Base64 is widely used on the Internet, as it plays a significant role in connecting binary and text data: *from embedding media/images/videos in URLs and HTML pages to ensuring compatibility between 7-bit protocols like older versions of [**SMTP**](https://en.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol).*

### How does it work?
Base64 encoding introduces an overhead of roughly 33%, as it turns each 3-byte group to a 4-byte group by following these steps:

**1. Dividing:** Split the binary data into groups of 3 bytes (24 bits), with the last one potentially having 1-2 bytes.

**2. Converting:** Turn each 24-bit group to 4x6-bit groups, these 6-bit groups are then mapped to 8-bit ASCII characters using a [lookup table](https://media.geeksforgeeks.org/wp-content/uploads/20200520142906/1461.png).

**3. Padding:** If the last group contains fewer than 3 bytes, the encoded output is padded with equal signs ('=') for proper alignment.

### How about an example?
The following image illustrates the steps involved in encoding **"Hi\n"**:

<img src="https://www.redhat.com/rhdc/managed-files/sysadmin/2022-08/30_printable_base64.png">

## Usage
Make sure you first clone the repository, and then build the project using the Makefile:
```bash
git clone https://github.com/TheAcebyte/base64-c.git
cd base64-c
make
```

To run the program, enter the following command:
```bash
./main <encode/decode>
```

From there, your terminal will wait for you to input a string before outputting your requested result.

## License
Licensed under the [**MIT** license](LICENSE).