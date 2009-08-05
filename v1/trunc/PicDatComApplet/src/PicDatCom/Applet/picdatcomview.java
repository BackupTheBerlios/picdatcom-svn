package PicDatCom.Applet;

import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import java.net.*;
import java.io.*;
import PicDatCom.*;

public final class picdatcomview extends JApplet implements Runnable {

	private static final long serialVersionUID = 1L;
	
	private static String Image_source_param = "Image_source";
	
	private String			Image_source;
	private Container		contentPane;
	private Dimension		size;
	private URL				url;
	private URLConnection	connection;
	private byte			byte_buffer[];
	private int 			byte_buffer_length;
	private int 			byte_buffer_offset;
	private int				byte_buffer_read	= 1000;
	private int				max_length 			= 5 * 1048576;
	private InputStream 	in_stream;
	private JProgressBar	progressbar 		= new JProgressBar(JProgressBar.HORIZONTAL);
	private PicDatComImage 	image;
	private BufferedImage 	jimage;
	private ImageIcon 		icon = null; 
	private Image			image_show;
	
	@Override
	public void init(){
		int read_length;
		
		System.out.println(System.getProperty("os.arch"));
		System.out.println(System.getProperty("os.name"));
		
		size = getSize();
		contentPane = getContentPane();
		
		Image_source = getParameter(Image_source_param);
		
		if(Image_source == null){
			contentPane.setLayout(new GridLayout(1, 1));
			contentPane.add(new JLabel("No " + Image_source_param + " Parameter are set !!!"));
		}else{
			try{
				url = new URL(Image_source);
			}catch(MalformedURLException e){
				contentPane.setLayout(new GridLayout(1, 1));
				contentPane.add(new JLabel(Image_source_param + " Parameter is not a valid URL"));	
				url = null;
				return;
			}
			
			try{
				connection			= url.openConnection();
				byte_buffer_length	= connection.getContentLength();
				
				
				if(byte_buffer_length > 8 && byte_buffer_length < max_length){
					byte_buffer			= new byte[byte_buffer_length];
					byte_buffer_offset = 0;
					in_stream	= new BufferedInputStream(connection.getInputStream());
					
					read_length = 8;
					for(byte_buffer_offset = 0; byte_buffer_offset < 8; ){
						byte_buffer_offset 	+= in_stream.read(byte_buffer, byte_buffer_offset, read_length);
						read_length = 8 - byte_buffer_offset;
					}
					
					if(byte_buffer[0] == -1 && byte_buffer[1] == 0x4F){
						// This is perhaps a jpeg2000 codestream. 
						progressbar.setMinimum(0);
						progressbar.setMaximum(byte_buffer_length);
						progressbar.setValue(8);
						progressbar.validate();
						contentPane.add(progressbar);
						
						Thread t = new Thread(this);
						t.start();										
					}else{
						contentPane.add(new JLabel("The filetype is unknown"));
					}
				}
				
			}catch(IOException e){
				contentPane.setLayout(new GridLayout(1, 1));
				contentPane.add(new JLabel("Can not connect to the Image_source URL"));	
				url = null;
				return;				
			}
			
		}
	}
	
	
	@Override
	public void run() {
		int read_length;
		try{
			for(; byte_buffer_offset < byte_buffer_length; ){
				if((byte_buffer_offset + byte_buffer_read) >= byte_buffer_length){
					read_length = byte_buffer_length - byte_buffer_offset;
				}else{
					read_length = byte_buffer_read;
				}
				byte_buffer_offset 	+= in_stream.read(byte_buffer, byte_buffer_offset, read_length);
				progressbar.setValue(byte_buffer_offset);
				progressbar.validate();
			}
			//try{
				image 	= new PicDatComImage(byte_buffer);
				jimage 	= image.getdirectImage();
				image.delete_PicDatComImage();
				image = null;
				
				image_show = jimage.getScaledInstance(size.width, size.height, Image.SCALE_DEFAULT);
				jimage.flush();
				jimage = null;
				
				icon = new ImageIcon(image_show);
				contentPane.remove(progressbar);
				contentPane.add(new JLabel(icon));
				contentPane.validate();
			//}catch(UnsatisfiedLinkError e){
			//	contentPane.remove(progressbar);
			//	contentPane.add(new JLabel("Your OS or Architektur is not supported. "));
			//	contentPane.validate();
			//}
			
		}catch(IOException e){
			
		}
	}

}
