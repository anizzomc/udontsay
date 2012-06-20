import java.io.Console;
import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class TCPHexa {
	private static Console console;
	private static Socket socket;
	
	public static void main(String[] args) throws Exception {
		if(args.length < 2){
			throw new IllegalArgumentException("not enogth parameters");
		}
		
		socket = new Socket(InetAddress.getByName(args[0]), Integer.parseInt(args[1]));
		OutputStream output = socket.getOutputStream();
		
		new Thread(new Runnable() {
			public void run() { 
				try {
				InputStream inputStream = socket.getInputStream();
				
				while(true) {
					try {
						int c = inputStream.read();
						if (c == -1){
							break;
						}
						System.out.println("Received: " + Integer.toHexString(c));	
					} catch(Exception e){
						System.out.println(e);
					}
			}
		} catch(IOException e){
			System.out.println(e);
		}
		}}).start();
		
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

