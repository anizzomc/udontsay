This is an implementation of a monolitic kernel that will handle serial port
Folder IMPL:
	Here is the Implementation of the kernel.
Folder HOST:
	Here is an Java Program that gets ascii input and transforms it to
	hexadecimal and then send the data to the host specified.
	
	$> java TCPHexa localhost 4444
	0a 0b 0c 0d ff

	Will send those hexadecimal values througt a tcp connection.


Testing:
	Start qemu in the following way:

	$> qemu -serial tcp::4444,server -fda disk.img


	Star TCPHexa in the same way

	$> java TCPHexa localhost 4444

	Wait until VM starts...


	Write characters....


Mas datos