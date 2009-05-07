/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package PicDatCom;

import java.awt.image.ComponentColorModel;
import java.awt.image.DataBuffer;
import java.awt.color.ColorSpace;
import java.awt.image.WritableRaster;
import java.awt.image.DataBufferFloat;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;


/**
 *
 * @author uwe_work
 */
public class PicDatComImage{
    
    //private static String dll_path = "C:\\Dokumente und Einstellungen\\uwe_work\\Eigene Dateien\\Visual Studio 2008\\Projects\\PicDatCom\\v1\\trunc\\Debug\\PDC.dll";
    //private static String dll_path = "/home/uwe/programmieren/eclipse/PicDatCom/Debug/libPicDatCom.so";
    private static String dll_path = "/home/uwe/EclipseProjects/picdatcom/Debug/libpicdatcom.so";

    static { 
        System.load(dll_path);
    } 
    
    private long pointer = 0;
    
    private WritableRaster  raster;
    private DataBufferFloat databuffer;
    
    private static native long create_structur(String path);
    
    private static native long delete_structur(long pointer);
    
    private static native int get_width(long pointer);
    
    private static native int get_height(long pointer);
    
    private static native float[] get_RGB( long pointer, float[] RGB);
    
    private static native int[] get_RGB( long pointer, int[] RGB);
    
    private int width;
    
    private int height;
    
    private int size;
    
    private ComponentColorModel colormodel;
    
    
    public PicDatComImage(String path){
        
        pointer = create_structur(path);
        width   = get_width(pointer);
        height  = get_height(pointer);
        size    = width * height;
        

    }
    
    public BufferedImage getImage(){
       BufferedImage image;
       
       colormodel = new ComponentColorModel(   ColorSpace.getInstance(ColorSpace.CS_sRGB), 
                                                false,false, ComponentColorModel.OPAQUE,
                                                DataBuffer.TYPE_FLOAT);                                                  
        raster = colormodel.createCompatibleWritableRaster(width, width); 
        databuffer = (DataBufferFloat)raster.getDataBuffer();
        get_RGB(pointer, databuffer.getData());
        
        image = new BufferedImage(colormodel, raster, false, null);
        
        return image;
    }
    
    public BufferedImage getdirectImage(){
       BufferedImage image;    
       DataBufferInt databufferint;
       
       image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
       databufferint = (DataBufferInt)image.getTile(0, 0).getDataBuffer();
       get_RGB(pointer, databufferint.getData());
       
       return image;
    }
}
