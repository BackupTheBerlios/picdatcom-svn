/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package picdatcomgui;

import java.io.File;
import java.awt.image.BufferedImage;
import javax.swing.JInternalFrame;
import PicDatCom.PicDatComImage;

/**
 *
 * @author uwe_work
 */
public class Picture_jpeg2000 implements Picture {

    private BufferedImage image;
    private JInternalFrame frame;
    private PicDatComImage picdatcom;
            
    public Picture_jpeg2000(File file){
        frame = new JInternalFrame(file.getName(), true, true);
        
    }
    
    public BufferedImage   getImage(){
        return image;
    }
    
    public JInternalFrame  getFrame(){
        return frame;
    }

}
