/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package picdatcomgui;

import java.io.File;

/**
 *
 * @author uwe_work
 */
public class Controller {

    private PicDatComGuiView view;

    public Controller(PicDatComGuiView view){
        this.view = view;
    }
    
    public void openfile(File file){
        /*
         * Open jpeg2000 file
         */
        if(file.getAbsolutePath().endsWith("jpc")){
            Picture_jpeg2000 pic = new Picture_jpeg2000(file);
            view.add_JInternalFrame(pic.getFrame());
        }
    }
}
