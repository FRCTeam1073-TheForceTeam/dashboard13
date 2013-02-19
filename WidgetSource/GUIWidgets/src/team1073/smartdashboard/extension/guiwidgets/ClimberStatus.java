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

public class ClimberStatus extends StaticWidget{
    private boolean isClimberEngaged;
    public final BooleanProperty newVal = new BooleanProperty(this, "Is Climber Engaged", false);
    public static final DataType[] TYPES = {DataType.BOOLEAN};
    
    public ClimberStatus () {isClimberEngaged = false;}
    
    @Override
    protected void paintComponent (Graphics graphics) {
        Graphics2D g = (Graphics2D) graphics;
        if(!isClimberEngaged) {
            graphics.setColor(Color.BLACK);
            graphics.fillRect(10, 10, 165, 100);
        }
        else {
            
            g.setStroke(new BasicStroke (2.0f));
            graphics.setColor(Color.GREEN);     
            graphics.fillRect(10, 10, 160, 100);
            graphics.setColor(Color.BLACK);
            Font font = new Font("Arial", Font.BOLD, 16);
            graphics.setFont(font);
            graphics.drawString("CLIMBER", 51, 57);
            graphics.drawString("ENGAGED", 48, 75);
            graphics.drawRect(10, 10, 160, 100);
        }
        

    }
    
    public void setValue(Object o) {
       boolean b = isClimberEngaged;
       
       try{b = (Boolean) o;}
       catch(Exception e){
       
       System.out.println("ClimberStatus setValue exception " + e);
       }
       
       isClimberEngaged = b;
       repaint();
    }

    @Override
    public void init() {
       isClimberEngaged = false;
       setPreferredSize(new Dimension(400,130));
    }

    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
