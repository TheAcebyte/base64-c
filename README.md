# Base64 Encoder/Decoder in C
## About
This repository features a **Base64** encoder and decoder written in pure C.

## Base64
### What is Base64?
Base64 is an encoding scheme that takes in arbitrary binary data and outputs printable ASCII text.

### Why is it used?
Base64 is quite prevalent on the Internet, as it plays a significant role in connecting binary and text data: *from embedding media/images/videos in URLs and HTML pages to ensuring compatibility between 7-bit protocols like older versions of [**SMTP**](https://en.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol).*

### How does it work?
Base64 encoding causes an overhead of roughly 33%, as it turns each 3-byte group to a 4-byte group by following the below rules:

**1. Dividing:** Split the binary data into groups of 3 bytes (24 bits), with the last one potentially having 1-2 bytes.

**2. Converting:** Turn each 24-bit group to 4x6-bit groups, which are then converted to 4x8-bit groups by mapping them to specific ASCII characters using a [lookup table](https://media.geeksforgeeks.org/wp-content/uploads/20200520142906/1461.png).

**3. Padding:** In case the last group does not have enough bytes to map to a 4-byte output, the encoded text is padded with equal signs "=".

### How about an example?
The following image demonstrates the steps it takes to encode **"Hi\n"**:

<img src="https://www.redhat.com/rhdc/managed-files/sysadmin/2022-08/30_printable_base64.png">

## Usage
Make sure you first clone the repository and run the Makefile:
```
git clone https://github.com/TheAcebyte/base64-c.git
cd base64-c
make
```

To run the script, just enter the following command:
```./main <encode/decode>```

From there, your terminal will wait for you to input a string before outputting your requested result.

## License
Licensed under the [**MIT** license](LICENSE).