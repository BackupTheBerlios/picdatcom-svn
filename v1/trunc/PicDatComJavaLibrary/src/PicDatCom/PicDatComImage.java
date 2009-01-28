/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package PicDatCom;

import java.awt.image.ComponentColorModel;
import java.awt.image.DataBuffer;
import java.awt.color.ColorSpace;

/**
 *
 * @author uwe_work
 */
public class PicDatComImage{
    
    private static String dll_path = "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2008\\Projects\\PicDatCom\\v1\\trunc\\Debug\\PDC.dll";
        
    static { 
        System.load(dll_path);
    } 
    
    private long pointer = 0;
    
    private static native long create_structur(String path);
    
    private static native long delete_structur(long pointer);
    
    private static native int get_width(long pointer);
    
    private static native int get_height(long pointer);
    
    private static native float[] get_RGB(float[] RGB);
    
    private int width;
    
    private int height;
    
    private int size;
    
    private ComponentColorModel colormodel;
    
    
    public PicDatComImage(String path){
        
        pointer = create_structur(path);
        width   = get_width(pointer);
        height  = get_height(pointer);
        size    = width * height;
        
        System.out.println("height = " + height +"\nwidth = " + width);
        /*
        colormodel = new ComponentColorModel(   ColorSpace.getInstance(ColorSpace.CS_sRGB), 
                                                false,false, ComponentColorModel.OPAQUE,
                                                DataBuffer.TYPE_FLOAT);                                                  
         */
    }
    
    
    
}
