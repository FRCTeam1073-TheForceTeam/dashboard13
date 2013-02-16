/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package team1073.smartdashboard.extension.guiwidgets;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.properties.IntegerProperty;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.lang.Math;
/**
 *
 * @author Kate
 * Nick Also Helped :)
 */
public class Speedometer extends StaticWidget{
    private final int maxSpeed = 20;
    private final int minSpeed = 0;
    private int speed;
    public final IntegerProperty newVal = new IntegerProperty(this, "Speed", 0);
    public static final DataType[] TYPES = {DataType.NUMBER};
    
    @Override
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
        g2.setColor(Color.BLACK);
        Color c = new Color(255, 255, 255);
        g.setColor(c);
        Color d = new Color(255, 200, 200);
        g.setColor (d);
        Color e = new Color(255, 230, 230);
        g.setColor (e);
        int radius = 150;
        g2.drawArc(0, 75, radius, radius, -180, -180);
        float angle = (speed / (maxSpeed - minSpeed) * 180);
        float endpointx = (float)(Math.cos(Math.toRadians(angle)) * radius/2);
        float endpointy = (float)(Math.sin(Math.toRadians(angle)) * radius/2);

        if(Math.abs(speed) > 50) {
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
       
       try{d = ((Number)o).intValue();}
       catch(Exception e){
           
           System.out.println("Speedometer setValue exception " + e);
       }
              
       speed = d;
       
       repaint();
    }
    
    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
