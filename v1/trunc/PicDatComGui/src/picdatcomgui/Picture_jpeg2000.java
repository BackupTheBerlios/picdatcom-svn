/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package picdatcomgui;

import java.io.File;
import java.awt.image.BufferedImage;
import javax.swing.JInternalFrame;
import PicDatCom.PicDatComImage;
import com.sun.media.jai.widget.DisplayJAI;
import javax.swing.JScrollPane;
import java.io.FileInputStream;
import java.io.IOException;

/**
 *
 * @author uwe_work
 */
public class Picture_jpeg2000 implements Picture {

    private BufferedImage   image;
    private JInternalFrame  frame;
    private PicDatComImage  picdatcom;
    private JScrollPane     scrollpane;

    private DisplayJAI display;
            
    public Picture_jpeg2000(File file){
        frame       = new JInternalFrame(file.getName(), true, true);
        scrollpane  = new JScrollPane();
        byte byte_stream[] = open_from_file(file);
        picdatcom   = new PicDatComImage(byte_stream);

        image   = picdatcom.getdirectImage();
        display = new DisplayJAI(image);
        scrollpane.getViewport().add(display);
        frame.add(scrollpane);
    }
    
    public BufferedImage   getImage(){
        return image;
    }
    
    public JInternalFrame  getFrame(){
        return frame;
    }

    private byte[] open_from_file(File file){
        
        byte byte_stream[] = null;
        long length, read_length, read_now;

        length = file.length();
        byte_stream = new byte[(int)length];
        try{
            FileInputStream in = new FileInputStream(file);
            for(read_length = 0, read_now = 0; read_length < length;){
                read_now = length - read_length;
                read_length += in.read(byte_stream, (int)read_length, (int)read_now);

            }

        }catch(IOException e){
            return null;
        }

        return byte_stream;
    }

}
