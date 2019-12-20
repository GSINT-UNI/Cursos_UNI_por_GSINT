import java.awt.*;
import java.awt.image.BufferedImage;

import java.io.*;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

public class LoadImage {
    public static void main(String args[]) {
        int[][] myImg = getMatrixOfImage("./test3.jpg");
        /*
        for(int i = 0; i < myImg.length; i++) {
            for(int j = 0; j < myImg[i].length; j++) {
                System.out.printf("%d %d : %d # ", i, j, myImg[i][j]);
                System.out.printf("bin: " + Integer.toBinaryString(myImg[i][j]));
                System.out.println(" # red: " + Integer.toBinaryString(myImg[i][j] & 0x00ff0000));
            }
            System.out.println("");
        }
        */
        int[][] myImgGS = toGrayScale(myImg, false);

        saveImageFromMatrix(myImgGS, "./pepito3.jpg");

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
            System.err.println("ERROR AL GRABAR");
            System.err.println(e);
        }
    }

    public static int[][] getMatrixOfImage(String filename) {
        BufferedImage bufferedImage = null;
        try {
            bufferedImage = ImageIO.read(new File(filename));
        } catch (IOException e) {
            System.err.println("Error al cargar el archivo");
            System.err.println(e);
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

    private static int paintItBlack(int argb, boolean _alpha_) {
        int annn, alpha, red, green, bleu;
        bleu = argb & 0xff;
        green = (argb & 0xff00)>>8;
        red = (argb & 0xff0000)>>16;
        if (_alpha_) alpha = argb & 0xff000000;
        else alpha = 0xff000000;
        int n = (bleu + green + red) / 3;
        
        annn = alpha + n + (n<<8) + (n<<16);

        return annn;
    }

    public static int[][] matrixToGrayScale(int[][] matrix, boolean _alpha_){
        int maxX = matrix.length;
        int maxY = matrix[0].length;
        int [][] pixels = new int[maxX][maxY];

        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                pixels[i][j] = paintItBlack(matrix[i][j], _alpha_);
            }
        }

        return pixels;
    }
}