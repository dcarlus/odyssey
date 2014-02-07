
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.Scanner;

public class Main {
	public static void main(String args[]) throws IOException {

		ServerSocket socket = null;
		Socket client = null;
		OutputStream os = null;
		
		// Mettre le chemin du fichier des clés à envoyer
		File f = new File("res/Io.keys");
		Scanner sc = new Scanner(f);
		try {
			socket = new ServerSocket(1234);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		boolean connected = false;
		System.out.println("Server Up");
		try {
			client = socket.accept();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		assert (client != null);
		
		if (client.isConnected()) {
			
			System.out.println("Client Connected");
			try {
				os = client.getOutputStream();
			} catch (IOException e) {
				e.printStackTrace();
			}
			assert (os != null);
			
			long fileLength = f.length();
			ByteBuffer bos = ByteBuffer.allocate(Long.SIZE / 8);
			bos.putLong(fileLength);

			byte longByte[] = bos.array();
			os.write(longByte);
			while (sc.hasNext()) {
				String data = sc.nextLine();
				byte dataByte[] = data.getBytes();
				os.write(dataByte.length);
				os.write(dataByte);
			}

			os.close();
			sc.close();
			return;
		}
	}

}
