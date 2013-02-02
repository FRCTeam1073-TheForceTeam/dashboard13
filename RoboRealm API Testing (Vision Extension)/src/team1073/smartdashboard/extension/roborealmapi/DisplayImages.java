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
    BufferedImage image = null;
    
    
    @Override
    public void init() {
        
        task = new CameraThread();
        this.setPreferredSize(new Dimension(640, 480));

        task.addPropertyChangeListener(new PropertyChangeListener()
            {
                @Override
                public void propertyChange(PropertyChangeEvent evt){
                    if ("progress".equals(evt.getPropertyName())){
                        
                        try
                        {
                            image = task.getSavedImage();
                            
                            if(image != null)
                            {
                                repaint();
                            }
                        }
                        catch (Exception e)
                        {
                            System.out.println("Exception: " + e.toString());
                        }
                    }
                    else
                    {
                        System.out.println("We made it to the else!  " + evt.getPropertyName());
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
        g.setColor(Color.ORANGE);
        g.drawImage(image, 0, 0, null);
    }
}
