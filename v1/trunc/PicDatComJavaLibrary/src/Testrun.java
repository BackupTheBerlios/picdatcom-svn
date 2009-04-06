/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.image.BufferedImage;
import PicDatCom.*;
/**
 *
 * @author uwe_work
 */
public class Testrun {

    PicDatComImage image;
    BufferedImage bimage;
    
    //String testfile = "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2008\\Projects\\PicDatCom\\prototype\\bdk\\image.jpc";
    String testfile = "/home/uwe/programmieren/picdatcom/prototype/bdk/image.jpc";

    public static void main(String[] args){
        new Testrun();
    }
    
    Testrun(){
        image   = new PicDatComImage(testfile);
        bimage  = image.getdirectImage(); 
        
        System.out.println("Ich lebe");
    }
}
