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
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.lang.Math;
/**
 *
 * @author Kate
 * Nick Also Helped :)
 * Don't Forget Keenan
 * ____━━____┓━╭━━━━━╮
____━━____┗┓|::::::^━━━^
____━━____━┗|:::::|｡◕‿‿ ◕｡|
____━━____━━╰O--O-O--O﻿ NYAN CAT
 */
public class Speedometer extends StaticWidget{
    private final int maxSpeed = 3700;
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
        System.out.println("Speed equals" + speed);
        Graphics2D g2 = (Graphics2D) g;
        int radius = 75;
        float angle = ((float) (maxSpeed - Math.abs(speed)) / (float)(maxSpeed - minSpeed)) * 180;
        //if the angle passes -90 degrees or 90 degrees make angle 90 or -90
        if (angle > 180) {
            
            angle = 180;
        }
        if (angle < 0) {
            angle = 0;
        }
        
        System.out.println("Angle equals" + angle);
        float endpointx = 75 + 
                (float)((Math.cos(Math.toRadians(angle))) * radius);
        float endpointy = 150 - 
                (float)((Math.sin(Math.toRadians(angle))) * radius);
        System.out.println("endpointx: " + (int) endpointx + " endpointy: " + (int) endpointy);

        Font font = new Font("Arial", Font.BOLD, 16);
        g2.setFont(font);
        g2.drawString("Speed: " + Integer.toString(Math.abs((int)speed)), 47, 180);
        if(Math.abs(speed) > 3700) {
            g2.setColor(Color.RED);
            g2.fillArc(0, 75, 150, 150, 0, 180);
        }
        else {
            //g2.drawString("Angle: " + Integer.toString(((int)angle)), 47, 200);
            Color a = new Color(255,74 + (int)angle, 74 + (int)angle);
            g2.setColor(a);
            g2.fillArc(0, 75, 150, 150,(int)angle, 180-(int)angle);
        }

        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(3.0f));
        g2.drawLine((int)75, (int)150,(int)endpointx, (int)endpointy);
        g2.drawLine(0,150, 150, 150);
        g2.setColor(Color.BLACK);        
        g2.drawArc(0, 75, 2*radius, 2*radius, 180, -180);   
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
