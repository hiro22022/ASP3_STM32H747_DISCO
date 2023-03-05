# -*- coding: utf-8 -*-

module TECSFlow
  def print_indent indent
    print "  " * indent
  end

  class TECSFlow
  #@celltypes
  #@cells
  #@composites
  #@functions
    def print_flow
      @active_cells = get_active_cells
      @active_cells.each{|cell|
        cell.print_flow_active
      }
    end

    def get_active_cells
    end
    def get_non_printed_cells
    end
  end

  class Celltype
  end
  class EntryPort
  end

  class Cell
  #@celltype
  #@joins
    def print_flow_active file, b_develop_composite
      indent = 0
      if @celltype.is_active? then
        @celltype.get_call_ports{ |port|
          port.each_func{|func|
            if ! func.is_called? then
              func.print_flow file, b_develop_composite, (indent+1)
            end
          }
        }
      end
    end
  end

  class Func
    def print_flow file, b_develop_composite, indent
      print_indent indent
      @calling_funcs.each{|func|
        if func.is_call_func? then
          print func.name, '\n'
          @cell.print_flow @entry, func, (indent+1)
        else
          print func.name, " -> "
          func.print_flow indent
        end
      }
    end
  end

  class Composites
  end

end

