open Ppxlib;

let parse_declarations:
  (string, string) =>
    result(
      list(Parsetree.expression),
      [ | `Invalid_value(string) | `Not_found],
    );

let render_when_unsupported_features: (string, string) => Parsetree.expression
