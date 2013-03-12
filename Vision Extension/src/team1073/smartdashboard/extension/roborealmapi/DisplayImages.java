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
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import javax.swing.JSlider;



/**
 *
 * @author Greg
 */
public class DisplayImages extends StaticWidget{

    CameraThread task = null;
    BufferedImage image = null;
    VisionProccesing vision = null;
    RR_API api = null;
    
    
    @Override
    public void init() {
        
        task = new CameraThread();
        vision = new VisionProccesing();
        //this.setPreferredSize(new Dimension(800, 600));
        this.setPreferredSize(new Dimension(640, 480));
        api = task.getApi();
        
        //KILLED THE SLIDER HERE MAJOR CHANGE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        task.addPropertyChangeListener(new PropertyChangeListener()
            {
                @Override
                public void propertyChange(PropertyChangeEvent evt){
                    if ("progress".equals(evt.getPropertyName())){
                        try
                        {
                            image = task.getSavedImage();
                            double targetRatio = task.getTargetRatio();
                            double underneathH = task.getUnderneathH();
                            double targetH = task.getTargetH();
                            try {
                            image = vision.processImage(image, underneathH, targetRatio, targetH);//proccesing
                            
                            }
                            catch(Exception e) {
                               System.out.println(e.getStackTrace()); 
                            }
                            
                            
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
