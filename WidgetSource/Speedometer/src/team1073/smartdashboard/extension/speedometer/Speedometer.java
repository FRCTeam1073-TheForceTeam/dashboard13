/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.speedometer;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.IntegerProperty;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;

/**
 *
 * @author Kate
 */
public class Speedometer extends StaticWidget{
    private int speed;
    public final IntegerProperty newVal = new IntegerProperty(this, "Speed", 0);
    public static final DataType[] TYPES = {DataType.NUMBER};
    
    public void init() {
        speed = 0;
        setPreferredSize(new Dimension(200,150));
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D) g;
        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(3.0f));
        g2.drawLine(0,150, 150, 150);
        
        if(Math.abs(speed) > 3500) {
            g2.setColor(Color.RED);
            g2.fillArc(0, 75, 150, 150, 0, 180);
        }
        else {
            int x = Math.abs(speed);
            double angleRad = Math.acos(x/75);
            if(speed < 0){

            }
            else{
                
            }
        }
    }
    
    public void setValue(Object o) {
        int d = speed;
       
       try{d = ((Number)o).intValue();;}
       catch(Exception e){}
       
       speed = d;
       
       repaint();
    }
    
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
