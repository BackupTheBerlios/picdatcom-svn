/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import PicDatCom.*;
/**
 *
 * @author uwe_work
 */
public class Testrun {

    PicDatComImage image;
    
    String testfile = "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2008\\Projects\\PicDatCom\\prototype\\bdk\\image.jpc";
    
    public static void main(String[] args){
        new Testrun();
    }
    
    Testrun(){
        image = new PicDatComImage(testfile);
        
        System.out.println("Ich lebe");
    }
}
