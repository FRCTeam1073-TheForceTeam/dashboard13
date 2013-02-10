package ClimberStatus;

import edu.wpi.first.smartdashboard.gui.StaticWidget;
import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.properties.BooleanProperty;
import edu.wpi.first.smartdashboard.types.DataType;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.Font;
import javax.swing.JFrame;

public class ClimberStatus extends StaticWidget{
    private boolean isClimberEngaged;
    public final BooleanProperty newVal = new BooleanProperty(this, "Is Climber Engaged", false);
    public static final DataType[] TYPES = {DataType.BOOLEAN};
    
    public ClimberStatus () {isClimberEngaged = false;}
    
    @Override
    protected void paintComponent (Graphics graphics) {
        
        if(!isClimberEngaged) {
            graphics.setColor(Color.BLACK);
            graphics.fillRect(10, 10, 200, 75);
        }
        else {
            graphics.setColor(Color.GREEN);     
            graphics.fillRect(10, 10, 200, 75);
            graphics.setColor(Color.BLACK);
            graphics.drawString("CLIMBER ENGAGED", 65, 45);
        }
        

    }

    public void setValue(Object o) {
       boolean b = isClimberEngaged;
       
       try{b = (Boolean) o;}
       catch(Exception e){}
       
       isClimberEngaged = b;
       repaint();
    }

    @Override
    public void init() {
       isClimberEngaged = false;
       setPreferredSize(new Dimension(50,50));
    }

    @Override
    public void propertyChanged(Property prprt) {
        setValue(prprt.getValue());
    }  
}
