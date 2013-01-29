/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.roborealmapi;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.Property;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import javax.imageio.ImageIO;
import java.awt.image.MemoryImageSource;
import java.awt.Image;
import java.awt.image.ImageObserver;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;


/**
 *
 * @author Greg
 */
public class DisplayImages extends StaticWidget{

    CameraThread task = null;
    
    
    @Override
    public void init() {
        
        task = new CameraThread();
        this.setPreferredSize(new Dimension(100, 100));

        task.addPropertyChangeListener(new PropertyChangeListener()
            {
                @Override
                public void propertyChange(PropertyChangeEvent evt){
                    if ("progress".equals(evt.getPropertyName())){
                        JPanel pic = null;
                        try
                        {
                            BufferedImage image;
                            Image otherImage;
                            image = task.getSavedImage();
                            otherImage = (Image) image;
                            
                            if(image != null)
                            {
                                //DOES NOT WORK - g is null
                                /*pic = new JPanel();
                                pic.setPreferredSize(new Dimension(640,480));
                                JFrame frame = new JFrame();
                                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                                frame.add(pic);
                                frame.setVisible(true);
                                Graphics g = pic.getGraphics();
                                g.drawImage(otherImage, 0, 0, observy);
                                frame.add(pic);*/
                                repaint();
                            }
                        }
                        catch (Exception e)
                        {
                            System.out.println("Image JLabel assignment exception\n");
                        }

                        if (pic != null)
                        {
                            add(pic);
                        }
                    }
                }
                
            }
        );
        
        task.execute();
        
        
    }

    @Override
    public void propertyChanged(Property prprt) {
        
    }
    
    @Override
    public void paintComponent(Graphics g)
    {
        BufferedImage image;
        image = task.getSavedImage();
        g.setColor(Color.ORANGE);
        //g.fillRect(0, 0, getBounds().width, getBounds().height);
        g.drawImage(image, 0, 0, null);
    }
}
