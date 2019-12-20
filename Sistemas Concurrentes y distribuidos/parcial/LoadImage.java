import java.awt.*;
import java.awt.image.BufferedImage;

import java.io.*;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class LoadImage {
    public static void main(String args[]) {
        int[][] myImg = getMatrixOfImage("./test2.jpg");

        for(int i = 0; i < myImg.length; i++) {
            for(int j = 0; j < myImg[i].length; j++) {
                //System.out.printf("%d %d : %d # ", i, j, myImg[i][j]);
            }
            //System.out.println("");
        }

        saveImageFromMatrix(myImg, "./pepito.jpg");

    }

    public static void saveImageFromMatrix(int[][] matrix, String filename) {
        int width = matrix.length;
        int height =  matrix[0].length;
        
        BufferedImage bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                bufferedImage.setRGB(i, j, matrix[i][j]);
            }
        }
        File outputfile = new File(filename);
        try {
            ImageIO.write(bufferedImage, "jpg", outputfile);
        }
        catch(Exception e) {
            System.out.println("ERROR AL GRABAR");
            System.out.println(e);
        }
    }

    public static int[][] getMatrixOfImage(String filename) {
        BufferedImage bufferedImage = null;
        try {
            bufferedImage = ImageIO.read(new File(filename));
        } catch (IOException e) {
            System.out.println("Error al cargar el archivo");
            return null;
        }

        int width = bufferedImage.getWidth(null);
        int height = bufferedImage.getHeight(null);
        int[][] pixels = new int[width][height];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                pixels[i][j] = bufferedImage.getRGB(i, j);
            }
        }
    
        return pixels;
    }

}