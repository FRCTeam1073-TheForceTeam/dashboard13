/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.Property;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import javax.imageio.ImageIO;
import java.awt.image.MemoryImageSource;
import java.awt.Image;


/**
 *
 * @author Greg
 */
public class DisplayImages extends StaticWidget{

    @Override
    public void init() {
        
        RR_API roboApi = new RR_API();
        roboApi.connect("localhost");
        Dimension size = new Dimension(640, 480);
        int length = size.height*size.width*3;  //one byte for each r, g, or b value
        int[] pixels = roboApi.getImage("processed");
        //byte[] pixels = new byte[length];
       // size = roboApi.getImage((String)"source", pixels, length);
        //pixels = roboApi.getImage("processed");
        
        try { 
            MemoryImageSource source;
            source = new MemoryImageSource(size.width, size.height, pixels, 0, size.width);
            source.setAnimated(true);
            BufferedImage image = new BufferedImage(size.width, size.height, BufferedImage.TYPE_INT_RGB);
            //Image image = createImage(source);
            image.setRGB(0, 0, size.width, size.height, pixels, 0, size.width);
        //InputStream in = new ByteArrayInputStream(pixels, 0, size.height*size.width);
        //BufferedImage image = ImageIO.read(in);
        //BufferedImage image = ImageIO.getImageReadersBySuffix("bmp").next().read(0);        
        ImageIO.write(image, "bmp", new File("C:/images/test.bmp"));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        //Bitmap image = BitmapFactory.decodeByteArray(pixels, 0, length);
    }

    @Override
    public void propertyChanged(Property prprt) {
        
    }
    
}
