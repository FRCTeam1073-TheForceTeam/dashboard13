package team1073.smartdashboard.extension.guiwidgets;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.BooleanProperty;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.Font;
import java.awt.Graphics2D;
import javax.swing.JFrame;

public class ShooterLockOn extends StaticWidget{
    private boolean isShooterLockedOn;
    public final BooleanProperty newVal = new BooleanProperty(this, "Is Shooter Locked On", false);
    public static final DataType[] TYPES = {DataType.BOOLEAN};
    
    public ShooterLockOn () {isShooterLockedOn = false;}
    
    @Override
    protected void paintComponent (Graphics graphics) {
        Graphics2D g = (Graphics2D) graphics;
        if(!isShooterLockedOn) {
            graphics.setColor(Color.RED);
            graphics.fillRect(10, 10, 200, 75);
            graphics.setColor(Color.BLACK);
            Font font = new Font("Arial", Font.BOLD, 32);
            graphics.setFont(font);
            graphics.drawString("ENGAGING", 30, 55);
            
        }
        else {
            
            g.setStroke(new BasicStroke (2.0f));
            graphics.setColor(Color.GREEN);     
            graphics.fillRect(10, 10, 200, 75);
            graphics.setColor(Color.BLACK);
            Font font = new Font("Arial", Font.BOLD, 32);
            graphics.setFont(font);
            graphics.drawString("LOCKED ON", 16, 55);
            graphics.drawRect(10, 10, 200, 75);
        }
        

    }
    
    public void setValue(Object o) {
       boolean b = isShooterLockedOn;
       
       try{b = (Boolean) o;}
       catch(Exception e){
       
       System.out.println("ShooterStatus setValue exception " + e);
       }
       
       isShooterLockedOn = b;
       repaint();
    }

    @Override
    public void init() {
       isShooterLockedOn = false;
       setPreferredSize(new Dimension(240,130));
    }

    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
