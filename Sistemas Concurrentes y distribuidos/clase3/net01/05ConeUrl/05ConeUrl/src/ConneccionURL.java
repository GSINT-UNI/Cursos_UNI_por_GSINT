import java.io.*;
import java.net.*;
import java.util.*;
 
 
public class ConneccionURL {
    public static void main(String[] args){
        try{
            String urlName;
            if (args.length > 0) urlName = args[0];
            else urlName = "http://www.google.com";

            URL url = new URL(urlName);
            URLConnection connection = url.openConnection();


            connection.connect();

            // print header fields

            Map<String, List<String>> headers = connection.getHeaderFields();
            for (Map.Entry<String, List<String>> entry : headers.entrySet()){
                String key = entry.getKey();
                for (String value : entry.getValue())
                System.out.println(key + ": " + value);
            }

            // print convenience functions

            System.out.println("----------");
            System.out.println("getContentType: " + connection.getContentType());
            System.out.println("getContentLength: " + connection.getContentLength());
            System.out.println("getContentEncoding: " + connection.getContentEncoding());
            System.out.println("getDate: " + connection.getDate());
            System.out.println("getExpiration: " + connection.getExpiration());
            System.out.println("getLastModifed: " + connection.getLastModified());
            System.out.println("----------");

            Scanner in = new Scanner(connection.getInputStream());

            // print first ten lines of contents
            for (int n = 1; in.hasNextLine() && n <= 10; n++)
                System.out.println(in.nextLine());
            if (in.hasNextLine()) System.out.println(". . .");
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    public static String base64Encode(String s){
        ByteArrayOutputStream bOut = new ByteArrayOutputStream();
        Base64OutputStream out = new Base64OutputStream(bOut);
        try{
            out.write(s.getBytes());
            out.flush();
        }
        catch (IOException e){
        }
        return bOut.toString();
    }
}

