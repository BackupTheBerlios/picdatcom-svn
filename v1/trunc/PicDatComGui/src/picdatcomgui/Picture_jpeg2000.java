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
        picdatcom   = new PicDatComImage(file.getAbsolutePath());

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

}
