/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package picdatcomgui;

import java.awt.image.BufferedImage;
import javax.swing.JInternalFrame;

/**
 *
 * @author uwe_work
 */
public interface Picture {

    BufferedImage   getImage();
    JInternalFrame  getFrame();
}
