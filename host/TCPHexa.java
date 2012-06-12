import java.io.Console;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class TCPHexa {
	private static Console console;
	private static Socket socket;
	
	public static void main(String[] args) throws NumberFormatException, UnknownHostException, IOException{
		if(args.length < 2){
			throw new IllegalArgumentException("not enogth parameters");
		}
		
		socket = new Socket(InetAddress.getByName(args[0]), Integer.parseInt(args[1]));
		OutputStream output = socket.getOutputStream();
		console = System.console();
		String line;
		
		try {
		while(true){
			if((line = console.readLine()) != null){
				String[] parts = line.split(" ");
				for(String s:parts){
					Integer i = Integer.parseInt(s, 16);
					output.write(i);
					output.flush();
					System.out.println("Sent: " + s);
				}
			}
		}
		} finally {
			socket.close();
		}
		
	}
}

